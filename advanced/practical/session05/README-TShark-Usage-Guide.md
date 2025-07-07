# TShark Usage Guide

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Basic Usage](#basic-usage)
- [Common Options and Examples](#common-options-and-examples)
- [Filtering Packets](#filtering-packets)
- [Saving Captures](#saving-captures)
- [Analyzing Saved Captures](#analyzing-saved-captures)
- [Advanced Features](#advanced-features)
- [Conclusion](#conclusion)

## Introduction

TShark is the command-line version of Wireshark, a network protocol analyzer. It captures packet data from a live network or a saved capture file, and displays the packet information in detail. TShark can be used to troubleshoot network problems, analyze network performance, and more.

## Installation

### On Linux

Install TShark using your distribution's package manager. For example:

- **Debian/Ubuntu:**

  ```sh
  sudo apt-get update
  sudo apt-get install tshark
  ```

- **CentOS/RHEL:**

  ```sh
  sudo yum install wireshark
  ```

### On macOS

Install TShark using Homebrew:

```sh
brew install wireshark
```

### On Windows

Download the Wireshark installer from the [official website](https://www.wireshark.org/) and ensure you select the TShark component during installation.

## Basic Usage

To capture packets on a network interface, you need to run TShark with superuser privileges. The basic syntax is:

```sh
sudo tshark -i <interface>
```

For example, to capture packets on the `eth0` interface:

```sh
sudo tshark -i eth0
```

## Common Options and Examples

### Display Interface List

To list all available network interfaces:

```sh
tshark -D
```

### Capture with Specific Filters

To capture only TCP packets:

```sh
sudo tshark -i eth0 -f "tcp"
```

### Limit the Number of Packets

To capture only a specific number of packets:

```sh
sudo tshark -i eth0 -c 100
```

### Display Packet Information

To display detailed information about each packet:

```sh
sudo tshark -i eth0 -V
```

## Filtering Packets

### Capture Filters

Capture filters are set before capturing and cannot be changed during the capture. They use the syntax of tcpdump.

- Capture only HTTP traffic:

  ```sh
  sudo tshark -i eth0 -f "tcp port 80"
  ```

- Capture traffic from a specific host:

  ```sh
  sudo tshark -i eth0 -f "host 192.168.1.1"
  ```

### Display Filters

Display filters are applied to captured packets. They use Wireshark’s display filter syntax.

- Display only TCP packets:

  ```sh
  sudo tshark -i eth0 -Y "tcp"
  ```

- Display packets from a specific IP:

  ```sh
  sudo tshark -i eth0 -Y "ip.src == 192.168.1.1"
  ```

## Saving Captures

### Save to a File

To save captured packets to a file:

```sh
sudo tshark -i eth0 -w capture.pcap
```

### Read from a File

To read packets from a saved capture file:

```sh
tshark -r capture.pcap
```

## Analyzing Saved Captures

### Summary Statistics

To get summary statistics from a capture file:

```sh
tshark -q -z io,stat,1 -r capture.pcap
```

### Protocol Hierarchy

To display the protocol hierarchy statistics:

```sh
tshark -q -z io,phs -r capture.pcap
```

### Conversations

To show all conversations in a capture file:

```sh
tshark -q -z conv,ip -r capture.pcap
```

## Advanced Features

### Extracting Fields

To extract specific fields from packets:

```sh
tshark -r capture.pcap -T fields -e frame.number -e ip.src -e ip.dst
```

### Using Multiple Interfaces

To capture from multiple interfaces simultaneously:

```sh
sudo tshark -i eth0 -i wlan0
```

### Ring Buffer

To use a ring buffer to save captures in multiple files:

```sh
sudo tshark -i eth0 -b filesize:10000 -b files:10 -w capture.pcap
```

This command creates a ring buffer with 10 files, each with a maximum size of 10 MB.

### Display Protocol Hierarchy Statistics

Display a summary of protocol hierarchy statistics during or after a capture:

```sh
tshark -q -z io,phs -r capture.pcap
```

### Display Endpoints Statistics

Show a list of endpoints (e.g., IP addresses) and their statistics:

```sh
tshark -q -z endpoints,ip -r capture.pcap
```

### Follow TCP Stream

Extract the data from a specific TCP stream:

```sh
tshark -r capture.pcap -q -z follow,tcp,ascii,0
```

### Extract HTTP Objects

Extract HTTP objects from the capture file:

```sh
tshark -r capture.pcap --export-objects http,/path/to/export/directory
```

### Analyze DNS Queries

Filter and analyze DNS queries:

```sh
tshark -r capture.pcap -Y "dns.flags.response == 0" -T fields -e frame.time -e ip.src -e dns.qry.name
```

### Extract RTP Streams

Analyze and extract RTP streams:

```sh
tshark -r capture.pcap -q -z rtp,streams
```

### Monitor HTTP Traffic

Monitor HTTP traffic with detailed display of HTTP headers:

```sh
sudo tshark -i eth0 -Y http -V
```

### Filter by VLAN

Capture packets on a specific VLAN:

```sh
sudo tshark -i eth0 -f "vlan 10"
```

### Analyze TCP Performance

Analyze TCP performance metrics such as round-trip time (RTT):

```sh
tshark -r capture.pcap -q -z io,stat,1,"AVG(tcp.analysis.ack_rtt)tcp.analysis.ack_rtt"
```

### Decode as Specific Protocol

Force TShark to decode a specific port as a particular protocol:

```sh
tshark -r capture.pcap -d tcp.port==8888,http
```

### Extract VoIP Calls

Extract and display VoIP call data:

```sh
tshark -r capture.pcap -q -z voip,calls
```

### Save Capture with Specific Interval

Capture packets and save them into multiple files with a specific time interval:

```sh
sudo tshark -i eth0 -b duration:60 -w capture-%Y%m%d%H%M%S.pcap
```

### Count Packet Types

Count the number of different packet types in a capture:

```sh
tshark -r capture.pcap -q -z io,stat,0,"COUNT(frame)frame"
```

### Extract Fields to CSV

Extract specific fields and save them to a CSV file:

```sh
tshark -r capture.pcap -T fields -E header=y -E separator=, -e frame.number -e ip.src -e ip.dst -e tcp.port > output.csv
```

### Analyze ICMP Traffic

Filter and analyze ICMP traffic:

```sh
tshark -r capture.pcap -Y "icmp" -T fields -e frame.time -e ip.src -e ip.dst -e icmp.type -e icmp.code
```

---

TShark is a powerful command-line tool for network traffic capture and analysis. It offers many features for filtering, saving, and analyzing network packets. By mastering TShark, you can perform comprehensive network diagnostics and gain deeper insights into network behavior.

---

For more detailed information and advanced usage, refer to the [TShark documentation](https://www.wireshark.org/docs/man-pages/tshark.html).
