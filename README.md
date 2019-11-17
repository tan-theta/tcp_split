# tcp_split
A tool written in C that splits a large pcap file into multiple pcap files where each pcap file contains a single tcp connection and are ordered by timestamp.

## Installation

Clone the repository. Makefile is provided.
Requires "tshark" to run.
```bash
apt-get install tshark
```

## Usage

Command line switches:

-i file_path: (Mandatory) Specifies a pcap file as input.

-o directory_path: (Mandatory) Specifies a directory to output pcap files to.

-f ip: (Optional) If this option is given, ignore all traffic that is not from or to the specified source IP.

-j file_path: (Optional) If this option is given, all non-TCP traffic should be stored into a single pcap file. Otherwise, all non-TCP traffic should be ignored.

```bash
./tcp_split -i test.pcap -o /root/Desktop/output -f 45.79.50.193 -j /root/Desktop/output/non_tcp.pcap
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
