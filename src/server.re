module Server = Simple_httpd.Server;
module Response = Simple_httpd.Server.Response;
module Address = Simple_httpd.Server.Address;

let (_args, parameters) = Server.args();

let listens = [Address.make(~addr="127.0.0.1", ~port=8080, ())];
let server = Server.create(parameters, ~listens);

/* echo request */
Server.add_route_handler(server, Server.Route.(exact("echo") @/ return), req =>
  Response.make_string(Format.asprintf("echo:@ %a@\n@.", Request.pp, req))
);

Array.iter(
  listener => Printf.printf("listening on http://%s:%d\n%!", listener.addr, listener.port),
  Server.listens(server),
);

Server.run(server);
