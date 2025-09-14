{
  inputs,
  pkgs,
  pyproject-toml,
  uv-lock,
}: let
  inherit (inputs) uv2nix pyproject-nix pyproject-build-systems;
  workspace = uv2nix.lib.workspace.loadWorkspace {
    # Manually filtering minimal workspace files for more cache efficiency.
    # Use of `workspaceRoot = ./.;` will include all files which is not
    # necessary for venv creation.
    workspaceRoot = pkgs.symlinkJoin {
      name = "filtered-python-root";
      paths = [
        (let
          pyproject = ../pyproject.toml;
        in
          pkgs.runCommand "copy-pyproject" {} ''
            mkdir -p $out
            cp ${pyproject-toml} $out/pyproject.toml
          '')
        (let
          uvlock = ../uv.lock;
        in
          pkgs.runCommand "copy-uvlock" {} ''
            mkdir -p $out
            cp ${uv-lock} $out/uv.lock
          '')
      ];
    };
  };
  overlay = workspace.mkPyprojectOverlay {
    sourcePreference = "wheel";
  };

  python = pkgs.python312;
  pythonSet =
    (pkgs.callPackage pyproject-nix.build.packages {
      inherit python;
    }).overrideScope
    (
      pkgs.lib.composeManyExtensions [
        pyproject-build-systems.overlays.default
        overlay
      ]
    );

  venv = pythonSet.mkVirtualEnv "development-scripts-default-env" workspace.deps.default;
in
  venv
