require "http/server"

server = HTTP::Server.new do |context|
  puts context.request.path
  context.response.content_type = "text/plain"
  context.response.print "Hello world! The time is #{Time.local} and you requested the path #{context.request.path}"
end

address = server.bind_tcp 8080
puts "Listening on http://#{address}"
server.listen