select  trunc(months_between(hire_date , trunc(hire_date, 'year'))/3,0) hire_quarter, count(*) total
from employees
group by trunc(months_between(hire_date , trunc(hire_date, 'year'))/3,0) ;

select rpad(first_name || ' ' || last_name, 20, ' ') full_name
from employees
order by length(first_name || ' ' || last_name) asc;

select country_id, ('('||street_address ||','|| city ||','|| state_province ||'-'|| postal_code||')') Address
from locations
where STREET_ADDRESS is not null and city is not null and STATE_PROVINCE is not null and POSTAL_CODE is not NULL
order by country_id asc, postal_code desc;

select department_id, job_id, min(hire_date) minimum_hire_date, max(hire_date) maximum_hire_date, round(avg(salary),2) Salary_avg
from EMPLOYEES
group by DEPARTMENT_ID, JOB_ID
having DEPARTMENT_ID is not null and JOB_ID is not null and avg(salary) >8000;

select first_name ||' '|| last_name full_name, hire_date
from EMPLOYEES
where lower(substr(first_name,1,1)) not in('a', 'e', 'i', 'o', 'u') and upper(last_name) not like '%B%' and to_char(hire_date, 'MM') = '11' 
order by full_name;


SELECT TO_CHAR(TRUNC(hire_date, 'Q'), 'Mon') as quarter_start, count(*)
FROM employees
GROUP BY TO_CHAR(TRUNC(hire_date, 'Q'), 'Mon');

SELECT TO_CHAR(hire_date, 'Q') as quarter, count(*) total
FROM employees
GROUP BY TO_CHAR(hire_date, 'Q')
ORDER BY quarter;