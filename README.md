# pkg-sync: The Interactive Arch Linux System Manager

**pkg-sync** is a robust and interactive C CLI tool for Arch Linux designed to keep your system in top shape. It goes beyond standard updates, offering deep health checks, a gamified system score, and interactive options to fix common issues. It's built for Arch users who value system stability, efficiency, and proactive maintenance.

---

## ✨ Why pkg-sync?

In the fast-paced world of Arch Linux, maintaining a healthy and secure system requires constant vigilance. `pkg-sync` simplifies this process by:

*   **Preventing Breakages**: Alerts you to critical Arch News updates that might require manual intervention, helping you avoid common pitfalls.
*   **Proactive Maintenance**: Identifies issues like orphaned packages, unmerged configuration files, and failed services *before* they cause problems.
*   **Time-Saving Automation**: Interactively guides you through fixing common issues, reducing the need to remember and type complex commands.
*   **System Awareness**: Gives you a clear overview of your system's recent activity and overall health with a simple score.
*   **Enhanced Reliability**: Ensures your `pacman` database is always accessible by detecting and offering to remove zombie lock files.

---

## 🚀 Features

*   **Interactive System Management**: `pkg-sync` isn't just a reporter; it proactively prompts you to fix detected issues (e.g., removing orphans, installing updates) and executes the necessary commands with your permission.
*   **System Health Score**: Get an immediate overview of your system's well-being with a score (0-100%) and a grade (A-F). This score is dynamically calculated based on pending updates, orphaned packages, failed services, and configuration conflicts, providing a clear metric for your system's health.
*   **Arch Linux News Integration**: Fetches and displays the latest Arch Linux news. This crucial feature keeps you informed about critical manual interventions or important announcements, helping you prevent system breakages during updates.
*   **Official Repository Updates**: Safely checks for pending updates in the official Arch repositories using `checkupdates`, ensuring your core system packages are always current without risking partial upgrades.
*   **AUR Updates**: Detects available updates for your Arch User Repository (AUR) packages (requires `yay` or similar helper), keeping your user-maintained software up-to-date.
*   **Orphaned Package Detection & Removal**: Identifies packages that were installed as dependencies but are no longer required by any explicitly installed software. `pkg-sync` offers an interactive option to safely remove these unnecessary packages, freeing up disk space and decluttering your system.
*   **Configuration Drift (.pacnew/.pacsave) Detection**: Scans your `/etc` directory for `.pacnew` and `.pacsave` files. These indicate configuration files that need your attention. `pkg-sync` alerts you to these conflicts and offers to launch `pacdiff` to help you merge changes.
*   **Failed System Services**: Quickly lists any `systemd` services that are currently in a failed state, helping you diagnose and resolve critical system issues.
*   **Pacman Lock Status**: Proactively checks for the presence of `/var/lib/pacman/db.lck`. If a lock file exists but `pacman` is not running (a "zombie lock"), `pkg-sync` warns you and offers to safely remove it, preventing future `pacman` operation failures.
*   **System Timeline (Last 48h)**: Provides a concise summary of your package management activity (installs, upgrades, removals) from `/var/log/pacman.log` over the last 48 hours. This helps you quickly diagnose what might have changed if your system starts misbehaving.
*   **Colorized Output**: All output is clearly formatted with ANSI color codes, making it easy to read and quickly identify important information and warnings.

## 📦 Prerequisites

*   `gcc`
*   `make`
*   `pacman`
*   `pacman-contrib` (for `checkupdates` and `pacdiff`)
*   `curl` (for fetching Arch News)
*   `yay` (or an alternative AUR helper like `paru` for AUR features)

## ⬇️ Installation

### From AUR (Recommended for Users)

The most convenient way to install `pkg-sync` is through the Arch User Repository (AUR) using your favorite AUR helper:

```bash
yay -S pkg-sync
# or paru -S pkg-sync
```

This method automatically handles compilation, dependencies, and system-wide installation.

### Manual Installation (for Developers/Testing)

If you're developing `pkg-sync` or prefer manual control:

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/Dacraezy1/pkg-sync.git
    cd pkg-sync
    ```

2.  **Build and Install using `makepkg`:**
    This command will compile the source, create a local Arch package (`.pkg.tar.zst`), and install it on your system using `pacman`. You will be prompted for your `sudo` password to perform the system-wide installation.
    ```bash
    makepkg -si
    ```

## ⌨️ Usage

After installation, simply run `pkg-sync` from any directory in your terminal. It will guide you through the health checks and interactive fixes:

```bash
pkg-sync
```

To display the version information:

```bash
pkg-sync --version
# or
pkg-sync -v
```

## 💡 Troubleshooting

*   **`pkg-sync: command not found`**: Ensure you've installed `pkg-sync` correctly, either via AUR or `makepkg -si`. Check your `PATH` environment variable if installed manually to `/usr/local/bin`.
*   **`Error: Unable to fetch news`**: Check your internet connection. Also ensure `curl` is installed (`sudo pacman -S curl`).
*   **`Error: Pacman is locked`**: `pkg-sync` will detect this! If `pkg-sync` detects a zombie lock file, it will offer to remove it interactively. If not, you can manually remove `/var/lib/pacman/db.lck` *after ensuring no `pacman` processes are running*.
*   **`Error: Failed to query AUR info`**: Ensure `yay` (or your configured AUR helper) is installed and functional.
*   **`'pacdiff' tool not found`**: Install `pacman-contrib` (`sudo pacman -S pacman-contrib`). `pkg-sync` will suggest this interactively.

## 🤝 Contributing

Contributions are welcome! If you have ideas for new features, bug fixes, or improvements:

1.  Fork the repository.
2.  Create a new branch (`git checkout -b feature/your-feature-name`).
3.  Make your changes and ensure they compile cleanly (`make clean && make`).
4.  Write clear commit messages.
5.  Push your branch (`git push origin feature/your-feature-name`).
6.  Open a Pull Request on GitHub.

---
**License:** MIT License
**Maintainer:** Dacraezy1 <younesaouzal18@gmail.com>
