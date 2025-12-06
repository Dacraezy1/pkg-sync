# pkg-sync: The Package Divergence Detector

**pkg-sync** is a lightweight C CLI tool for Arch Linux that performs a deep "health check" on your package ecosystem. It goes beyond standard updates to identify inconsistencies, orphans, and neglected AUR packages.

## Features

*   **Official Repo Updates**: Checks for updates safely (using `checkupdates`) without syncing the root database unnecessarily.
*   **AUR Updates**: Detects available updates for AUR packages.
*   **Orphan Detection**: Lists packages that were installed as dependencies but are no longer needed.
*   **AUR Health Check**:
    *   Identifies packages that have been flagged "out-of-date" by the maintainer.

## Prerequisites

*   `gcc`
*   `make`
*   `pacman`
*   `pacman-contrib` (for `checkupdates`)
*   `yay` (or another AUR helper, currently optimized for `yay`)

## Installation

```bash
git clone https://github.com/Dacraezy1/pkg-sync.git
cd pkg-sync
make
./pkg-sync
```
