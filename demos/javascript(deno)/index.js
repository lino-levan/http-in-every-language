import { serve } from "https://deno.land/std@0.133.0/http/server.ts";

const port = 8080;

const handler = (request) => {
  console.log(request)
  let body = `Hello world! The time is ${new Date().toTimeString()} and you requested the path ${request.url.split(":8080")[1]}`;

  return new Response(body, { status: 200 });
};

console.log(`Listening on http://127.0.0.1:${port}`);
await serve(handler, { port });