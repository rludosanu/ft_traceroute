# ft_traceroute

Print the route packets take to network host

## Synopsis

```
sudo ./ft_traceroute [-h] [-f first_ttl] [-m max_ttl] [-w waittime] [-q nqueries] [-I] [-U] [-p port] host
```

## Usage

```
-h
	Displays usage

-f first_ttl
	Set the initial time-to-live used in the first outgoing probe packet

-m max_ttl
	Set the max time-to-live used in outgoing probe packets

-w waittime
	Set the time (in seconds) to wait for a response to a probe

-q nqueries
	Set the number of probes per ttl to nqueries

-I
	Use ICMP ECHO instead of UDP datagrams

-U
	Use UDP ECHO (default)

-p port
	Protocol specific. For UDP and TCP, sets the base port number used in probes

host
	Destination host name or IP number
```
