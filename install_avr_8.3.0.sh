#!/bin/bash
# Install AVR GCC 8.3.0 toolchain

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PREFIX="${SCRIPT_DIR}/avr_toolchain"
BUILD_DIR="${SCRIPT_DIR}/avr_toolchain_build"
BINUTILS_VERSION="2.32"
GCC_VERSION="8.3.0"
AVR_LIBC_VERSION="2.0.0"

BINUTILS_URL="https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.bz2"
GCC_URL="https://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz"
AVR_LIBC_URL="https://download.savannah.gnu.org/releases/avr-libc/avr-libc-${AVR_LIBC_VERSION}.tar.bz2"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

log_info() {
    echo -e "${GREEN}[INFO]${NC} $*"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $*"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $*" >&2
}

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

check_dependencies() {
    log_info "Checking dependencies..."
    local missing_deps=()

    for dep in wget tar make gcc g++ bzip2; do
        if ! command_exists "$dep"; then
            missing_deps+=("$dep")
        fi
    done

    if [ ${#missing_deps[@]} -ne 0 ]; then
        log_error "Missing required dependencies: ${missing_deps[*]}"
        log_error "Please install them using your package manager."
        exit 1
    fi

    log_info "All dependencies found."
}

check_installed() {
    if [ -f "${PREFIX}/bin/avr-gcc" ] && command_exists "${PREFIX}/bin/avr-gcc"; then
        local version
        version=$("${PREFIX}/bin/avr-gcc" -dumpversion 2>/dev/null || echo "")
        if [ "$version" = "$GCC_VERSION" ]; then
            log_info "AVR GCC ${GCC_VERSION} is already installed at ${PREFIX}"
            log_info "To reinstall, remove ${PREFIX} and ${BUILD_DIR} directories"
            exit 0
        fi
    fi
}

cleanup() {
    local exit_code=$?
    if [ $exit_code -ne 0 ]; then
        log_error "Script failed. Build artifacts remain in ${BUILD_DIR}"
        log_warn "To retry, remove ${BUILD_DIR} and run again"
        log_warn "The downloaded files will be preserved"
    else
        if [ -d "$BUILD_DIR" ]; then
            log_info "Cleaning up build directory ${BUILD_DIR}..."
            rm -rf "$BUILD_DIR"
            log_info "Build directory cleaned up successfully."
        fi
    fi
}
trap cleanup EXIT

download_and_extract() {
    local url=$1
    local output_file=$2
    local extract_cmd=$3

    log_info "Downloading $(basename "$url")..."
    if [ -f "$output_file" ]; then
        log_warn "File already exists: $output_file (skipping download)"
    else
        wget --progress=bar:force:noscroll -O "$output_file" "$url" || {
            log_error "Failed to download $url"
            exit 1
        }
    fi

    log_info "Extracting $(basename "$output_file")..."
    $extract_cmd "$output_file" || {
        log_error "Failed to extract $output_file"
        exit 1
    }
}

build_binutils() {
    log_info "Building binutils ${BINUTILS_VERSION}..."
    cd "${BUILD_DIR}/binutils-${BINUTILS_VERSION}"

    mkdir -p obj-avr
    cd obj-avr

    log_info "Configuring binutils..."
    ../configure --prefix="$PREFIX" --target=avr --disable-nls || {
        log_error "binutils configure failed"
        exit 1
    }

    log_info "Building binutils (this may take a while)..."
    make -j"$(nproc)" || {
        log_error "binutils build failed"
        exit 1
    }

    log_info "Installing binutils..."
    make install || {
        log_error "binutils install failed"
        exit 1
    }

    cd "${BUILD_DIR}"
}

download_gcc_prerequisites() {
    log_info "Downloading GCC prerequisites..."
    cd "${BUILD_DIR}/gcc-${GCC_VERSION}"

    # GCC 8.3.0 prerequisites (using HTTPS instead of FTP)
    local gmp_version="6.1.0"
    local mpfr_version="3.1.4"
    local mpc_version="1.0.3"
    local isl_version="0.18"

    # URLs using HTTPS mirrors (avoiding FTP)
    local gmp_url="https://gmplib.org/download/gmp/gmp-${gmp_version}.tar.bz2"
    local mpfr_url="https://www.mpfr.org/mpfr-${mpfr_version}/mpfr-${mpfr_version}.tar.bz2"
    local mpc_url="https://ftp.gnu.org/gnu/mpc/mpc-${mpc_version}.tar.gz"
    # ISL from GNU mirror (infrastructure directory is available via HTTPS)
    local isl_url="https://gcc.gnu.org/pub/gcc/infrastructure/isl-${isl_version}.tar.bz2"

    # Alternative URLs if primary fails
    local gmp_alt="https://ftp.gnu.org/gnu/gmp/gmp-${gmp_version}.tar.bz2"
    local mpfr_alt="https://ftp.gnu.org/gnu/mpfr/mpfr-${mpfr_version}.tar.bz2"
    local isl_alt="https://libisl.sourceforge.io/isl-${isl_version}.tar.bz2"

    download_prereq() {
        local url=$1
        local alt_url=$2
        local filename=$3
        local linkname=$4

        if [ -e "$linkname" ]; then
            log_warn "Prerequisite $linkname already exists, skipping..."
            return 0
        fi

        log_info "Downloading $filename..."
        if ! wget --progress=bar:force:noscroll -O "$filename" "$url" 2>/dev/null; then
            if [ -n "$alt_url" ]; then
                log_warn "Primary URL failed, trying alternative..."
                if ! wget --progress=bar:force:noscroll -O "$filename" "$alt_url" 2>/dev/null; then
                    log_error "Failed to download $filename"
                    return 1
                fi
            else
                log_error "Failed to download $filename"
                return 1
            fi
        fi

        log_info "Extracting $filename..."
        local extract_cmd
        case "$filename" in
            *.tar.bz2) extract_cmd="tar xjf" ;;
            *.tar.gz) extract_cmd="tar xzf" ;;
            *) log_error "Unknown archive format: $filename"; return 1 ;;
        esac

        if ! $extract_cmd "$filename"; then
            log_error "Failed to extract $filename"
            return 1
        fi

        local package="${filename%.tar*}"
        log_info "Creating symlink $linkname -> $package"
        ln -sf "$package" "$linkname" || {
            log_error "Failed to create symlink $linkname"
            return 1
        }
    }

    # Download and link prerequisites
    download_prereq "$gmp_url" "$gmp_alt" "gmp-${gmp_version}.tar.bz2" "gmp" || exit 1
    download_prereq "$mpfr_url" "$mpfr_alt" "mpfr-${mpfr_version}.tar.bz2" "mpfr" || exit 1
    download_prereq "$mpc_url" "" "mpc-${mpc_version}.tar.gz" "mpc" || exit 1
    download_prereq "$isl_url" "$isl_alt" "isl-${isl_version}.tar.bz2" "isl" || exit 1

    log_info "All GCC prerequisites downloaded successfully."
}

build_gcc() {
    log_info "Building GCC ${GCC_VERSION}..."
    cd "${BUILD_DIR}/gcc-${GCC_VERSION}"

    download_gcc_prerequisites

    mkdir -p obj-avr
    cd obj-avr

    log_info "Configuring GCC..."
    ../configure \
        --prefix="$PREFIX" \
        --target=avr \
        --enable-languages=c,c++,lto \
        --disable-nls \
        --disable-libssp \
        --with-dwarf2 || {
        log_error "GCC configure failed"
        exit 1
    }

    log_info "Building GCC (this will take a very long time)..."
    make -j"$(nproc)" || {
        log_error "GCC build failed"
        exit 1
    }

    log_info "Installing GCC..."
    make install || {
        log_error "GCC install failed"
        exit 1
    }

    cd "${BUILD_DIR}"
}

build_avr_libc() {
    log_info "Building avr-libc ${AVR_LIBC_VERSION}..."
    cd "${BUILD_DIR}/avr-libc-${AVR_LIBC_VERSION}"

    mkdir -p obj-avr
    cd obj-avr

    log_info "Configuring avr-libc..."
    ../configure \
        --prefix="$PREFIX" \
        --build="$(../config.guess)" \
        --host=avr \
        --enable-debug-info=dwarf-2 || {
        log_error "avr-libc configure failed"
        exit 1
    }

    log_info "Building avr-libc..."
    make -j"$(nproc)" || {
        log_error "avr-libc build failed"
        exit 1
    }

    log_info "Installing avr-libc..."
    make install || {
        log_error "avr-libc install failed"
        exit 1
    }

    cd "${BUILD_DIR}"
}

verify_installation() {
    log_info "Verifying installation..."
    export PATH="${PREFIX}/bin:${PATH}"

    if ! command_exists "${PREFIX}/bin/avr-gcc"; then
        log_error "avr-gcc not found in ${PREFIX}/bin"
        exit 1
    fi

    local version
    version=$("${PREFIX}/bin/avr-gcc" -dumpversion 2>/dev/null || echo "")
    if [ "$version" != "$GCC_VERSION" ]; then
        log_error "Version mismatch: expected ${GCC_VERSION}, got ${version}"
        exit 1
    fi

    log_info "AVR GCC version: $version"
    "${PREFIX}/bin/avr-gcc" -v

    log_info ""
    log_info "${GREEN}Installation completed successfully!${NC}"
    log_info "Toolchain installed to: ${PREFIX}"
    log_info "Add to your PATH: export PATH=\"${PREFIX}/bin:\$PATH\""
}

main() {
    log_info "AVR GCC ${GCC_VERSION} Toolchain Installer"
    log_info "=========================================="

    check_dependencies
    check_installed

    mkdir -p "$PREFIX"
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    download_and_extract "$BINUTILS_URL" "binutils-${BINUTILS_VERSION}.tar.bz2" "tar xjf"
    download_and_extract "$GCC_URL" "gcc-${GCC_VERSION}.tar.gz" "tar xzf"
    download_and_extract "$AVR_LIBC_URL" "avr-libc-${AVR_LIBC_VERSION}.tar.bz2" "tar xjf"

    build_binutils
    build_gcc
    build_avr_libc

    verify_installation
}

main "$@"
