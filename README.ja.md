# UE Restart Command

Unreal Editor の保存、終了、再起動、Live Coding コンパイルを簡単に行うための Unreal Engine 5 プラグインです。

## 特徴

- **Editor 再起動** - 保存してから Editor を再起動
- **Editor 終了** - 保存してから Editor を終了
- **Live Coding コンパイル** - Live Coding で .cpp ファイルをコンパイル
- **パッケージ保存** - 全ての未保存パッケージを保存

## セットアップ手順

### 1. リポジトリのクローン

```bash
git clone https://github.com/SpirrowGames/UeRestartCommand.git
```

### 2. プラグインとして追加

1. プロジェクトのルートディレクトリに `Plugins` フォルダがない場合は作成します。
2. クローンした `UeRestartCommand` フォルダを `Plugins` フォルダの中にコピーします。
3. Unreal Editor を起動し、**Edit > Plugins** から "UE Restart Command" が有効になっていることを確認します。
4. Output Log に `Unreal Editor Restart Command - Python Module Loaded` が出力されていれば Python モジュールも読み込まれています。

> このプラグインは Python API を利用しているため、エンジンの標準プラグインである "Python Editor Script Plugin" が有効である必要があります。

## API について

このプラグインは C++/Blueprint での利用も可能ですが、基本的には Python から外部実行されることを想定しています。

### C++ クラス: `UEditorRestartLib`

Blueprint Function Library として実装されており、Python と Blueprint の両方から利用可能です。

| 関数 | 戻り値 | 説明 |
|------|--------|------|
| `SaveAllDirtyPackages()` | `bool` | 全ての未保存パッケージを保存 |
| `ExitEditor()` | `void` | Editor を終了（保存なし） |
| `RestartEditor()` | `void` | Editor を再起動（保存なし） |
| `SaveAndExitEditor()` | `void` | 保存してから Editor を終了 |
| `SaveAndRestartEditor()` | `void` | 保存してから Editor を再起動 |
| `CompileLiveCoding()` | `bool` | Live Coding でコンパイル |

### Python から使用

直接利用する場合は `unreal` パッケージから利用できます。

```py
import unreal

# Compile LiveCoding
unreal.EditorRestartLib.compile_live_coding()

# Save and Restart
unreal.EditorRestartLib.save_and_restart_editor()

# Save and Exit
unreal.EditorRestartLib.save_and_exit_editor()

# Save only
unreal.EditorRestartLib.save_all_dirty_packages() 

# Exit only
unreal.EditorRestartLib.exit_editor()

# Restart only
unreal.EditorRestartLib.restart_editor()
```

また、上記をラップした関数も起動時に自動でロードされます。  
Output Log の Python コンソールや、他の Pythonスクリプト内から直接呼び出す際に便利です。

```py
# Compile LiveCoding
compile_live_coding();

# Save and Restart
save_and_restart_editor()

# Save and Exit
save_and_exit()

# Save only
save_all_dirty_packages() 

# Exit only
exit_editor()

# Restart only
restart_editor()
```

### Blueprint から使用

1. Blueprint を開く
2. 右クリックして "Editor | Restart" カテゴリを探す
3. 以下の関数が利用可能です：
   - **Save All Dirty Packages** - 全て保存
   - **Exit Editor** - 終了
   - **Restart Editor** - 再起動
   - **Save And Exit Editor** - 保存して終了
   - **Save And Restart Editor** - 保存して再起動
   - **Compile Live Coding** - Live Coding のコンパイル

## ue-python-cli との組み合わせ

Unreal Editor への外部からの Python スクリプトの実行は標準的な方法 (`UnrealEditor-Cmd.exe` や `Python Remote Execution`) がありますが、[ue-python-cli](https://github.com/self-taught-code-tokushima/ue-python-cli) を利用することもできます。

`ue-python-cli` は CLI ツールであるため、Coding Agent からも簡単に利用できます。

### ue-python-cli の使い方

```bash
# ツールとしてインストールして利用
uv tool install git+https://github.com/self-taught-code-tokushima/ue-python-cli 
ue-python exec %python code%

# uvx で直接実行
uvx --from git+https://github.com/self-taught-code-tokushima/ue-python-cli ue-python exec %python code%
```

### 関数の実行

```bash
# Hot Reload (CompileLiveCoding)
ue-python exec "compile_live_coding()"

# Save and Restart
ue-python exec "save_and_restart_editor()"

# Save and Exit
ue-python exec "save_and_exit()"

# Save only
ue-python exec "save_all_dirty_packages()"

# Exit only
ue-python exec "exit_editor()"

# Restart only
ue-python exec "restart_editor()"
```

## プロジェクト構造

```
UeRestartCommand/
├── Content/
│   └── Python/
│       ├── init_unreal.py          # 起動時にラッパー関数をグローバルにロード
│       ├── compile_live_coding.py
│       ├── restart_editor.py
│       └── save_and_exit.py
│ 
├── Source/
│   └── UeRestartCommand/
│       ├── Public/
│       │   └── EditorRestartLib.h  # C++ API ヘッダー
│       ├── Private/
│       │   ├── EditorRestartLib.cpp         # C++ API 実装
│       │   └── UeRestartCommand.cpp         # モジュール実装
│       └── UeRestartCommand.Build.cs        # ビルド設定
├── UeRestartCommand.uplugin        # プラグイン定義
└── README.md                       # このファイル
```

## トラブルシューティング

### `AttributeError: module 'unreal' has no attribute 'EditorRestartLib'`

**原因**: プラグインが有効化されていないか、Editor が再起動されていません。

**解決方法**:
1. Editor で **Edit → Plugins** を開く
2. "UE Restart Command" を検索して有効化
3. Editor を再起動

### `Live Coding module is not available`

**原因**: Live Coding が無効化されています。

**解決方法**:
1. Editor で **Edit → Editor Preferences** を開く
2. **General → Live Coding** を有効化
3. Editor を再起動

### ビルドエラー: "Cannot open include file"

**原因**: 依存モジュールが不足しています。

**解決方法**: `UeRestartCommand.Build.cs` に以下が含まれているか確認：
```csharp
PrivateDependencyModuleNames.AddRange(new string[] {
    "UnrealEd",
    "LiveCoding"
});
```

## 必要な環境

- Unreal Engine 5.7 以上
- Windows 64-bit（現在のビルド設定）

## 参考リンク

- [Unreal Engine Python API](https://dev.epicgames.com/documentation/en-us/unreal-engine/PythonAPI)
- [Live Coding](https://dev.epicgames.com/documentation/en-us/unreal-engine/using-live-coding-to-recompile-unreal-engine-applications-at-runtime)
