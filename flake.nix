
{
  description = "C++ MP3 Player";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };

    in {
      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "mp3player";
        version = "1.0.0";

        src = self;

        nativeBuildInputs = [
          pkgs.pkg-config
          pkgs.wrapQtAppsHook
        ];

        buildInputs = [
          pkgs.qt6.qtbase
          pkgs.qt6.qtdeclarative
          pkgs.qt6.qtsvg
          pkgs.libglvnd
        ];

        buildPhase = ''
          g++ -std=c++20 -O2 -Wall -Wextra -I. \
            $(find . -name '*.cpp') \
            $(pkg-config --cflags --libs Qt6Widgets) \
            -o mp3player
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp mp3player $out/bin/mp3player
        '';
      };

      apps.${system}.default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/mp3player";
      };
    };
}
