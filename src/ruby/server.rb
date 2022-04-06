require 'socket'

port = 8080
server = TCPServer.new port
 
puts "Listening on http://127.0.0.1:#{port}"
while session = server.accept
  request = session.gets
 
  session.print "HTTP/1.1 200\r\n"
  session.print "Content-Type: text/html\r\n"
  session.print "\r\n"
  session.print "Hello world! The time is #{Time.now} and you requested the path #{request.split(" ")[1]}"
 
  session.close
end