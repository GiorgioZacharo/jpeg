#!/bin/bash

# Pass selected configuration.
CONF=${1:-"config_example"} 

~giorgio/ALADDIN/common/aladdin  $CONF ../dynamic_trace.gz $CONF


