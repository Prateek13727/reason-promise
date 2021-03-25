let countries: Js.Json.t = [%bs.raw
    {|
      {
        countries: [
          {
            id: 1,
            name: "Switzwerland",
          },
          {
            id: 2,
            name: "New Zealand",
          },
          {
            id: 3,
            name: "Ireland",
          },
        ]
      }
    |}     
  ];


  let places: Js.Json.t = [%bs.raw
    {|
      {
        places: [
          {
            id: 4,
            place: "The Fairy Pools, Isle of Skye, Scotland",
          },
          {
            id: 5,
            place: "Grand Canyon National Park, USA",
          },
          {
            id: 6,
            place: "Huacachina, Peru",
          },
        ]
      }
    |}
  ];
  

  let corporate_info: Js.Json.t = [%bs.raw
    {|
      {
        company_details: {
          name: "Slack Pvt Limited",
          brand_name: "Slack",
        }
      } 
    |}
  ];

  let country_ids: Js.Json.t = [%bs.raw 
  {|
    {
      data: [1, 2, 3]
    }
  |}
]

  let makePromise = (~json: Js.Json.t) => {
      Js.Promise.(
        make((~resolve, ~reject as _) => {
          resolve(. json)
        })
      )
      |> Promise.Js.fromBsPromise
      |> Promise.Js.toResult
  }

  let fetchData = () => makePromise(~json=country_ids)

  let fetchCountries = (
    ids: list(int), 
    
  ) =>  makePromise(~json=countries)

  let fetchPlaces = (
    ids: list(int), 
  ) => makePromise(~json=places)

  let fetchCorporateInfo = () =>  makePromise(~json=corporate_info)

