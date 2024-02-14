#!/bin/bash

conda build  "$@" \
      --skip-existing \
      --variants "{'cluster': ['hodges'], 'device': ['gpu']}" \
      --output-folder $HOME/test/channel
