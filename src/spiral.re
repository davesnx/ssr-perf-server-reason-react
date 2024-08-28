let wrapperWidth = 960.;
let wrapperHeight = 720.;
let cellSize = 10.;
let centerX = wrapperWidth /. 2.;
let centerY = wrapperHeight /. 2.;

type tile = {
  x: float,
  y: float,
  id: int,
};

let generateTiles = () => {
  let idCounter = ref(0);
  let angle = ref(0.0);
  let radius = ref(0.0);
  let tiles = ref([||]);
  let step = cellSize;

  while (radius.contents < min(wrapperWidth, wrapperHeight) /. 2.0) {
    let x = centerX +. cos(angle.contents) *. radius.contents;
    let y = centerY +. sin(angle.contents) *. radius.contents;

    if (x >= 0.0 && x <= wrapperWidth -. cellSize && y >= 0.0 && y <= wrapperHeight -. cellSize) {
      tiles := Array.append(tiles.contents, [|{x, y, id: idCounter.contents}|]);
      idCounter := idCounter.contents + 1;
    };

    angle := angle.contents +. 0.2;
    radius := radius.contents +. step *. 0.015;
  };

  tiles.contents;
};

[@react.component]
let make = () => {
  let tiles = generateTiles();
  let tileElements =
    Array.map(
      tile =>
        <div
          className="tile"
          key={string_of_int(tile.id)}
          style={ReactDOM.Style.make(
            ~left=string_of_float(tile.x) ++ "px",
            ~top=string_of_float(tile.y) ++ "px",
            (),
          )}
        />,
      tiles,
    );

  <div id="wrapper"> {React.array(tileElements)} </div>;
};
