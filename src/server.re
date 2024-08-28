let get = Tiny_httpd.add_route_handler(~meth=`GET);

let () = {
  let server = Tiny_httpd.create();
  let addr = Tiny_httpd.addr(server);
  let port = Tiny_httpd.port(server);

  get(
    server,
    Tiny_httpd.Route.(return),
    _req => {
      let html = ReactDOM.renderToString(<Spiral />);
      Tiny_httpd.Response.make_string(Ok(html));
    },
  );

  switch (Tiny_httpd.run(server, ~after_init=() => Printf.printf("Listening on http://%s:%d\n%!", addr, port))) {
  | Ok () => ()
  | Error(e) => raise(e)
  };
};
