module Utils {
  let resolveResult = (result: Belt.Result.t('a, Decco.decodeError), path): 'a => {
    switch (result) {
    | Ok(parsedData) => parsedData
    | Error(error) => failwith("failed " ++ path);
    }
  };
};

module Data  {
  [@decco]
  type t = {
    data: list(int)
  };
};

module Countries {
  [@decco]
  type country = {
    name: string,
    id: int
  };

  [@decco]
  type t = {
    countries: list(country)
  }
};

module Places {
  [@decco]
  type place = {
    place: string,
    id: int
  };

  [@decco]
  type t = {
    places: list(place)
  }
};

module CorporateInfo {
  [@decco]
  type companyDetails = {
    name: string,
    brand_name: string
  };

  [@decco]
  type t = {
    company_details: companyDetails
  }
};

let execute = () => {
    DummyRepo.fetchData()
    ->Promise.Js.get((json) => {
        switch(json) {
        | Ok(json) => {
            let {data}: Data.t = json -> Data.t_decode -> Utils.resolveResult("data")
            data -> DummyRepo.fetchCountries
             ->Promise.Js.get((json) => {
                switch(json) {
                  | Ok(json) => {
                     let {countries} : Countries.t = json -> Countries.t_decode -> Utils.resolveResult("countries")
                     let countryIds = countries -> Belt.List.map(({id}: Countries.country) => id);
                      countryIds -> DummyRepo.fetchPlaces
                      ->Promise.Js.get((json) => {
                          switch(json) {
                            | Ok(json) => {
                                let {places} : Places.t = json -> Places.t_decode -> Utils.resolveResult("places")
                                DummyRepo.fetchCorporateInfo()
                                ->Promise.Js.get((json) => {
                                    switch(json) {
                                      | Ok(json) => {
                                          let {company_details} = json -> CorporateInfo.t_decode -> Utils.resolveResult("company_details")
                                          Js.log4(data, countries, places, company_details)
                                      }
                                      | Error(error) => Js.log(error)
                                    }
                                })
                            }
                            | Error(error) => Js.log(error)
                          }
                      })
                  }
                  | Error(error) => Js.log(error)
                }
             })
        }
        | Error(error) => Js.log(error)
        }
    })
}

execute()