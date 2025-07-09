#!/bin/bash

for cc in gcc clang; do
for std in 11 14 17 20; do
  echo --------------------------------------------
  cmake --preset ${cc}-${std}
  cmake --build --preset ${cc}-${std}
  echo
done
done
