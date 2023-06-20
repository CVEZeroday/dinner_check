log_dir="./log"
log_prefix="logfile_$(date +%Y%m%d_%H%M%S)"
log_file="$log_dir/$log_prefix.log"

echo "Copying students data from main app..."
cp ../app/data . -r
nohup python3 -u app_qr.py > "$log_file" 2>&1 & 

echo "App started. Log file: $log_file"

sleep 1
cat $log_file

external_ip=$(curl -s http://checkip.amazonaws.com)

echo " * Running on http://$external_ip:8080"
