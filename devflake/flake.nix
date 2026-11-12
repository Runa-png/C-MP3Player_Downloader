{
  description = "Qt6 C++ development environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };

      qt = pkgs.qt6.env "qt6" [
        pkgs.qt6.qtbase
        pkgs.qt6.qtdeclarative
        pkgs.qt6.qttools
        pkgs.qt6.qtsvg
        pkgs.qt6.qtwayland
      ];

    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          # C++ toolchain
          gcc
          gdb
          cmake
          ninja
          pkg-config

          # Qt
          qt
          qtcreator

          # Open GL
          libGL
          libglvnd
        ];

        shellHook = ''
          echo "Entering Qt6 development environment"
        '';
      };
    };
}