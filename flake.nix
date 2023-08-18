{
  inputs = {
    nixpkgs.url = "nixpkgs";
    ft-nix = {
      url = "github:vinicius507/42-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs = {
    self,
    nixpkgs,
    ft-nix,
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
            overlays = [ft-nix.overlays.norminette];
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
    devShells = forEachSystem ({pkgs}: let
      mkShell = pkgs.mkShell.override {inherit (pkgs.llvmPackages_12) stdenv;};
    in {
      default = mkShell {
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
