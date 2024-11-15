TOTAL_START=$(date +%s)

sleep 5

TOTAL_END=$(date +%s)
echo "Total script duration: $((TOTAL_END - TOTAL_START)) seconds"