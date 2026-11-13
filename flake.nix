
{
  description = "C++ MP3 Player";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };

      pythonEnv = pkgs.python3.withPackages (ps: with ps; [
        yt-dlp
      ]);

    in {
      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "mp3player";
        version = "1.0.0";

        src = self;

        nativeBuildInputs = [
          pkgs.pkg-config
          pkgs.qt6.wrapQtAppsHook
        ];

        buildInputs = [
          pkgs.qt6.qtbase
          pkgs.qt6.qtdeclarative
          pkgs.qt6.qtsvg
          pkgs.libglvnd
        ];

        qtWrapperArgs = [
          "--prefix PATH : ${pythonEnv}/bin"
        ];

        buildPhase = ''
          g++ -std=c++20 -O2 -Wall -Wextra -I. \
            $(find . -name '*.cpp') \
            $(pkg-config --cflags --libs Qt6Widgets) \
            -o mp3player
        '';

        installPhase = ''
          mkdir -p $out/bin
          mkdir -p $out/share/mp3player/scripts

          cp mp3player $out/bin/mp3player
          cp -r scripts/*.py $out/share/mp3player/scripts/
        '';
      };

      apps.${system}.default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/mp3player";
      };
    };
}
