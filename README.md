# Client Model
A general purpose test client for any server.

This is a software including a library and a compiler for processing **SRC**(Send/Recv Cmd) Language, which is designed to write easy-reading scripts to test a server.

The language looks like this:
```
#This is an example of SRC Language

Send Command example

TCP("192.168.123.105",9531)

CMD QueryCommand SEND
  U16 ver := 100
  U16 cmd_type := 161
  U32 seq := 1234
  U32 len
  BEGIN(len)
  STR file_hash := "http://www.google.com"
  STR client_hash := UNHEX("1A2B3C4D5E6F")
  STR peer_id := "ABCDEF"
END CMD
```
The compiler can process the script and send QueryCommand to server at address 192.168.123.105:9531.

If there is a response, you can write more scripts to receive the package and decode it using SRC language.

This is very useful when you are developing a server without any test clients.
