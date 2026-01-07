select country_id, ('('||street_address ||','|| city ||','|| state_province ||'-'|| postal_code||')') Address
from locations
where STREET_ADDRESS is not null and city is not null and STATE_PROVINCE is not null and POSTAL_CODE is not NULL
order by country_id asc, postal_code desc;