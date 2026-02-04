"""
Unreal Editor を保存してから終了する Python スクリプト

UeRestartCommand プラグインの Python API
"""

import unreal


def save_and_exit_editor():
    """
    全ての未保存パッケージを保存してから Unreal Editor を終了します。

    この関数は C++ で実装された EditorRestartLib.save_and_exit_editor() を呼び出します。

    Example:
        >>> from save_and_exit import exit_editor
        >>> exit_editor()  # Editor が終了されます
    """
    print("Saving and exiting Unreal Editor...")
    unreal.EditorRestartLib.save_and_exit_editor()

def exit_editor():
    """
    Unreal Editor を終了します。

    この関数は C++ で実装された EditorRestartLib.exit_editor() を呼び出します。

    Example:
        >>> from save_and_exit import exit_editor
        >>> exit_editor()  # Editor が終了されます
    """
    print("Exiting Unreal Editor...")
    unreal.EditorRestartLib.exit_editor()
