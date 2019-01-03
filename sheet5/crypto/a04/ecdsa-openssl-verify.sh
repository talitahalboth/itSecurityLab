#!/bin/sh

/bin/echo -n "Verifying msg1: "
openssl dgst -ecdsa-with-SHA1 -verify vk.pem -signature msg1.sig msg1.txt

/bin/echo -n "Verifying msg2: "
openssl dgst -ecdsa-with-SHA1 -verify vk.pem -signature msg2.sig msg2.txt
