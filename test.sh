#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Function to log messages
log() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

pass() {
    echo -e "${GREEN}[PASS]${NC} $1"
}

fail() {
    echo -e "${RED}[FAIL]${NC} $1"
}

# Send SET command to a node
send_set() {
    local port=$1
    local key=$2
    local value=$3
    echo "SET $key $value" | nc localhost $port
}

# Send GET command to a node
send_get() {
    local port=$1
    local key=$2
    echo "GET $key" | nc localhost $port
}

# Wrapper to test if GET returns expected value
test_get() {
    local port=$1
    local key=$2
    local expected=$3
    result=$(send_get $port $key | tr -d '\n')
    if [[ "$result" == "$expected" ]]; then
        pass "GET $key on port $port => $result"
    else
        fail "GET $key on port $port => $result (expected $expected)"
    fi
}

# Start Testing
log "Running Distributed Key-Value Store Tests"
echo

# STEP 1: Basic SET from Node 9000
log "Step 1: SET to Node 9000"
send_set 9000 user1 alice
send_set 9000 user2 bob
send_set 9000 user3 carol
send_set 9000 user4 dave
send_set 9000 user5 elena
sleep 1

# STEP 2: GET from Node 9001
log "Step 2: GET from Node 9001 (replica)"
test_get 9001 user1 alice
test_get 9001 user2 bob
test_get 9001 user3 carol
test_get 9001 user4 dave
test_get 9001 user5 elena

# STEP 3: SET from Node 9001
log "Step 3: SET to Node 9001"
send_set 9001 city1 tokyo
send_set 9001 city2 seoul
send_set 9001 city3 beijing
send_set 9001 city4 bangkok
send_set 9001 city5 jakarta
sleep 1

# STEP 4: GET from Node 9000
log "Step 4: GET from Node 9000 (replica)"
test_get 9000 city1 tokyo
test_get 9000 city2 seoul
test_get 9000 city3 beijing
test_get 9000 city4 bangkok
test_get 9000 city5 jakarta

# STEP 5: Overwriting existing key
log "Step 5: Overwrite key test"
send_set 9000 user1 anthony
sleep 1
test_get 9001 user1 anthony

# STEP 6: Stress test with multiple keys
log "Step 6: Stress test with 30 keys"
for i in {1..30}; do
    send_set 9000 key$i value$i
done
sleep 1
all_pass=true
for i in {1..30}; do
    value=$(send_get 9001 key$i | tr -d '\n')
    if [[ "$value" != "value$i" ]]; then
        fail "Stress test failed for key$i"
        all_pass=false
    fi
done
if $all_pass; then
    pass "Stress test passed for all 30 keys (9000 ➜ 9001)"
fi

# STEP 7: Testing missing key
log "Step 7: Request non-existent key"
result=$(send_get 9000 nokey | tr -d '\n')
if [[ "$result" == "" ]]; then
    pass "GET nokey on port 9000 correctly returned empty"
else
    fail "GET nokey on port 9000 returned: $result"
fi

echo
log "✅ All automated tests completed."
