create table temp_dep(
    temp_department_id number(4,0) ,
    temp_location_id number (4,0),
    temp_department_name varchar2(100),
    address varchar2(200)
);

insert into temp_dep(temp_department_id, temp_location_id, temp_department_name) 
select department_id, location_id, department_name
from departments;

update temp_dep k2
SET
address = (
    select street_address || ', '
    || city || ', '
    ||  state_province || ', '
    || postal_code thikana
    from LOCATIONS k
    where k.location_id = k2.temp_location_id
    );

select temp_department_name, address
from temp_dep
order by temp_department_id;

rollback;
select *
from temp_dep;
drop table temp_dep purge;
commit;