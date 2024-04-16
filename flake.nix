{
  inputs = {
    nixpkgs.url = "nixpkgs";
  };
  outputs = {
    self,
    nixpkgs,
  }: let
    allSystems = [
      "x86_64-linux"
      "aarch64-linux"
    ];

    forEachSystem = f:
      nixpkgs.lib.genAttrs allSystems (system:
        f {
          pkgs = import nixpkgs {
            inherit system;
            overlays = builtins.attrValues self.overlays;
          };
        });
  in {
    checks = forEachSystem ({pkgs}: let
      norminetteCheck = check-name: src:
        pkgs.stdenvNoCC.mkDerivation {
          inherit src;
          name = "norminette-check-${check-name}";
          dontBuild = true;
          doCheck = true;
          checkPhase = with pkgs; ''
            ${norminette}/bin/norminette $src
          '';
          installPhase = "touch $out"; # Derivation must build an output.
        };
    in {
      norminette-check-mandatory = norminetteCheck "mandatory" ./mandatory;
      norminette-check-bonus = norminetteCheck "bonus" ./bonus;
    });
    overlays = {
      devshell = final: prev: {
        mkShell = prev.mkShell.override {inherit (final.llvmPackages_12) stdenv;};
      };
    };
    devShells = forEachSystem ({pkgs}: {
      default = pkgs.mkShell {
        packages = with pkgs; [
          bear
          clang-tools_12
          gnumake
          norminette
          valgrind
        ];
      };
    });
  };
}
