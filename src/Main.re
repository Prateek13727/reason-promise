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

let (let.await) = Promise.flatMapOk;

let fetchAllData = () => {
  let.await json = DummyRepo.fetchData();
  let {data}: Data.t = json->Data.t_decode->Utils.resolveResult("data");

  let.await json = DummyRepo.fetchCountries(data);
  let {countries}: Countries.t =
    json->Countries.t_decode->Utils.resolveResult("countries");
  let countryIds = countries->Belt.List.map(({id}: Countries.country) => id);

  let.await json = DummyRepo.fetchPlaces(countryIds);
  let {places}: Places.t =
    json->Places.t_decode->Utils.resolveResult("places");

  Promise.resolved(Ok((data, countries, places)));
};

let fetchDetails = () => {
  let.await json = DummyRepo.fetchCorporateInfo();
  let {company_details} =
    json->CorporateInfo.t_decode->Utils.resolveResult("company_details");

  Promise.resolved(Ok(company_details));
};

let execute = () => {
  Promise.allOk2(fetchAllData(), fetchDetails())
  ->Promise.mapOk((((data, countries, places), company_details)) => {
      Js.log4(data, countries, places, company_details)
    })
  ->Promise.mapError(Js.log)
  ->Promise.Js.get(ignore);
};

execute()