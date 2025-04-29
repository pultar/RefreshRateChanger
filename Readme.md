# RefreshRateChanger

Some LG OLED TVs in combination with NVIDIA graphics cards can have flickering. Changing the monitor refresh rate temporarily can help.

`RefreshRateChanger.exe` changes the monitor refresh rate to `BackupRefreshRate` and back to `TargetRefreshRate` after `Delay` seconds. The binary `QRes.exe` is required. Values are read from `RefreshRateChanger.yaml`, which has to be located in the same folder.`

Example configuration file.

```yaml
TargetRefreshRate: 144
BackupRefreshRate: 120
BinaryPath: "QRes.exe"
Delay: 5
```

The process can be automated to run after a reboot with Windows Task Scheduler. It is recommended to delay execution for 30 s or more and to set the work folder (Start in:) to the folder `RefreshRateChanger.exe` is located. A copy of `QRes.exe` is available together with the binary itself.
