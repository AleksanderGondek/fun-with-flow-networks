{ pkgs ? import <nixpkgs> {}, ... }:

pkgs.stdenv.mkDerivation {
  name = "killdozer";
  src = ./src;

  buildInputs = with pkgs; [ 
    busybox
    gcc
  ];

  buildPhase = ''
    g++ -std=c++14 -o killdozer *.cpp
  '';

  installPhase = ''
    mkdir -p $out
    cp killdozer $out/
  '';
}
