"""
Unreal Editor を保存してから再起動する Python スクリプト

UeRestartCommand プラグインの Python API
"""

import unreal


def save_all_dirty_packages():
    """全ての未保存パッケージを保存"""
    print("Saving all dirty packages...")

    success = unreal.EditorRestartLib.save_all_dirty_packages()

    if success:
        print("All packages saved successfully")
    else:
        print("Warning: Some packages may not have been saved")

    return success


def restart_editor():
    """Unreal Editor を再起動"""
    print("Restarting Unreal Editor...")

    unreal.EditorRestartLib.restart_editor()


def save_and_restart_editor():
    """保存と再起動を一度に実行"""
    print("Saving and restarting Unreal Editor...")

    unreal.EditorRestartLib.save_and_restart_editor()
