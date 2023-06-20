python_processes=$(ps aux | grep '[p]ython3 -u app_qr.py' | awk '{print $2}')

for pid in $python_processes; do
  kill $pid
done

echo "Processes killed: $python_processes"
