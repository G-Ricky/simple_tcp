if [ "x$1" == "x" ]; then
  echo 'usage: ./droprst.sh [PORT]'
  exit 1
fi
iptables -t filter -I OUTPUT -p tcp --dport "$1" --tcp-flags RST RST -j DROP