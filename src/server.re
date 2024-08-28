open Simple_httpd;

let (_args, parameters) = Server.args();

module Params = (val parameters);
Params.max_connections := 125;
Params.num_threads := 100;

let listens = [Address.make(~addr="127.0.0.1", ~port=8080, ())];
let server = Server.create(parameters, ~listens);

Server.add_route_handler(
  server,
  Route.(exact("hi") @/ return),
  _req => {
    let html = ReactDOM.renderToStaticMarkup(<Spiral />);
    Response.make_string(html);
  },
);

Array.iter(
  (listener: Address.t) => Printf.printf("listening on http://%s:%d\n%!", listener.addr, listener.port),
  Server.listens(server),
);

Server.run(server);
