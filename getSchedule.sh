#!/bin/sh

curl -X 'GET' \
  "https://www.thebluealliance.com/api/v3/event/$1/matches/simple" \
  -H 'accept: application/json' -H "X-TBA-Auth-Key: $2" > schedule.json
