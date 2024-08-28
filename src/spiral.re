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
  let rec generateTiles = (angle, radius, idCounter, acc) => {
    let x = centerX +. Js.Math.cos(angle) *. radius;
    let y = centerY +. Js.Math.sin(angle) *. radius;

    let newAcc =
      if (x >= 0.0
          && x <= wrapperWidth
          -. cellSize
          && y >= 0.0
          && y <= wrapperHeight
          -. cellSize) {
        [{x, y, id: idCounter}, ...acc];
      } else {
        acc;
      };

    let newRadius = radius +. cellSize *. 0.015;

    if (newRadius < Js.Math.min_float(wrapperWidth, wrapperHeight) /. 2.0) {
      generateTiles(angle +. 0.2, newRadius, idCounter + 1, newAcc);
    } else {
      newAcc;
    };
  };

  generateTiles(0.0, 0.0, 0, []);
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
               style={ReactDOM.Style.make(
                 ~left=string_of_float(tile.x) ++ "px",
                 ~top=string_of_float(tile.y) ++ "px",
                 (),
               )}
             />,
           tiles,
         ),
       ),
     )}
  </div>;
};
