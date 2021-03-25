// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var $$Promise = require("reason-promise/src/js/promise.bs.js");

var countries = {
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
      };

var places = {
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
      };

var corporate_info = {
        company_details: {
          name: "Slack Pvt Limited",
          brand_name: "Slack",
        }
      };

var country_ids = {
      data: [1, 2, 3]
    };

function makePromise(json) {
  return $$Promise.Js.toResult($$Promise.Js.fromBsPromise(new Promise((function (resolve, param) {
                        return resolve(json);
                      }))));
}

function fetchData(param) {
  return makePromise(country_ids);
}

function fetchCountries(ids) {
  return makePromise(countries);
}

function fetchPlaces(ids) {
  return makePromise(places);
}

function fetchCorporateInfo(param) {
  return makePromise(corporate_info);
}

exports.countries = countries;
exports.places = places;
exports.corporate_info = corporate_info;
exports.country_ids = country_ids;
exports.makePromise = makePromise;
exports.fetchData = fetchData;
exports.fetchCountries = fetchCountries;
exports.fetchPlaces = fetchPlaces;
exports.fetchCorporateInfo = fetchCorporateInfo;
/* Promise Not a pure module */