---
layout: project
type: project
image: akuloloia.github.io/images/388x208xsshot-5.png.pagespeed.gp+jp+jw+pj+js+rj+rp+rw+ri+cp+md.ic.1Ribf4Jo_X.png
title: SHA-1 Encryption
permalink: projects/SHA-1
date: 2015
labels:
  - C++
summary: I developed a program that runs SHA-1 encryption on input files.
---

<div class="ui small rounded images">
  <img class="ui image" src="../images/388x208xsshot-5.png.pagespeed.gp+jp+jw+pj+js+rj+rp+rw+ri+cp+md.ic.1Ribf4Jo_X.png">
  <img class="ui image" src="../images/micromouse-robot-2.jpg">
  <img class="ui image" src="../images/micromouse.jpg">
  <img class="ui image" src="../images/micromouse-circuit.png">
</div>

SHA-1 encryption is a hash function that takes a file, arragnes the data in a randomized manner and outputs a value in a specific number range.  This hash value is 160 bits long and is widely used as a cryptographic encryption function for storing passwords, error detection and comparing files.

For this project, I began by ensuring each piece of data was read into the program.  That included error checking, in the event the file did not exist, was entered incorrectly or was too large for my program to handle.  Afterwards, I placed each character the file contained into a character array, transmuted it into an integer array and passed it on the message digest function.  This would compute the hash value and return it to the user.



