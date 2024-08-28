type tile = {
  x: float,
  y: float,
  id: int,
};

let wrapperWidth = 960.0;
let wrapperHeight = 720.0;
let cellSize = 10.0;
let centerX = wrapperWidth /. 2.0;
let centerY = wrapperHeight /. 2.0;

let createTiles = () => {
  let tiles = ref([]);
  let angle = ref(0.0);
  let radius = ref(0.0);
  let idCounter = ref(0);

  while (radius^ < Js.Math.min_float(wrapperWidth, wrapperHeight) /. 2.0) {
    let x = centerX +. Js.Math.cos(angle^) *. radius^;
    let y = centerY +. Js.Math.sin(angle^) *. radius^;

    if (x >= 0.0 && x <= wrapperWidth -. cellSize && y >= 0.0 && y <= wrapperHeight -. cellSize) {
      tiles := [{x, y, id: idCounter^}, ...tiles^];
      idCounter := idCounter^ + 1;
    };

    angle := angle^ +. 0.2;
    radius := radius^ +. cellSize *. 0.015;
  };

  tiles^;
};

[@react.component]
let make = () => {
  let tiles = createTiles();

  <div id="wrapper">
    {React.array(
       Array.of_list(
         List.map(
           (tile: tile) =>
             <div
               key={string_of_int(tile.id)}
               className="tile"
               style={ReactDOM.Style.make(~left=string_of_float(tile.x), ~top=string_of_float(tile.y), ())}
             />,
           tiles,
         ),
       ),
     )}
  </div>;
};
