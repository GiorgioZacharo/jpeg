#!/bin/bash

# Pass selected configuration.
CONF=${1:-"conf"} 

~giorgio/ALADDIN/common/aladdin  $CONF ../dynamic_trace.gz $CONF


