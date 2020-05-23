{ pkgs ? import <nixpkgs> {}, ... }:

pkgs.stdenv.mkDerivation {
  name = "killdozer";
  src = ./.;

  buildInputs = with pkgs; [ 
    busybox
    gcc
    # Testing framework
    catch2
  ];

  preBuildPhases = ["preBuildPhase"];
  preBuildPhase = ''
    export ALL_SOURCES=''$(find ./src -regex '.*\.\(cpp\|hpp\)')
    export NO_MAIN_SOURCES=''$(find ./src -regex '.*\.\(cpp\|hpp\)' -not -name main.cpp)
    export TESTS_FILES=''$(find ./tests -regex '.*\.\(cpp\|hpp\)')
  '';

  buildPhase = ''
    g++ \
      -Wall \
      -Wextra \
      -Wpedantic \
      -std=c++14 \
      -o killdozer \
      ''${ALL_SOURCES}

    # Testing
    ln -s ${pkgs.catch2}/include/catch2/catch.hpp \
      tests/catch.hpp

    g++ \
      -w \
      -std=c++14 \
      -o test \
      ''${NO_MAIN_SOURCES} \
      ''${TESTS_FILES} \
      ./tests/catch.hpp
  '';

  doCheck = true;
  checkPhase = ''
    ./test
  '';

  installPhase = ''
    mkdir -p $out
    cp killdozer $out/
  '';
}
