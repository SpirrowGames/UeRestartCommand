"""
Live Coding でコンパイルを実行する Python スクリプト

UeRestartCommand プラグインの Python API

注意:
    Live Coding には制限があります：
    - ヘッダファイル (.h) の変更には対応していません
    - 新しいクラスの追加には対応していません
    - UPROPERTY、UFUNCTION の追加には対応していません

    これらの変更を行った場合は、フルビルド＆再起動が必要です。
"""

import unreal


def compile_live_coding():
    """
    Live Coding でコンパイルを実行します。

    この関数は C++ で実装された EditorRestartLib.compile_live_coding() を呼び出します。

    Returns:
        bool: Live Coding の開始に成功した場合 True、失敗した場合 False

    Example:
        >>> from compile_live_coding import compile_live_coding
        >>> success = compile_live_coding()
        >>> if success:
        ...     print("Live Coding compilation started")
    """
    print("Starting Live Coding compilation...")

    success = unreal.EditorRestartLib.compile_live_coding()

    if success:
        print("Live Coding compilation started successfully")
        print("Monitor the Output Log for compilation results")
    else:
        print("Failed to start Live Coding compilation")
        print("Please check that Live Coding is enabled in Editor Preferences")

    return success
