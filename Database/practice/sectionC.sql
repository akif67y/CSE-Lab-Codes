select country_id, count(city) cities, count(distinct STATE_PROVINCE) Provinces
from locations
group by country_id
having count(STATE_PROVINCE) >0 and count(city) >= 2 ;

select department_id
from JOB_HISTORY
where end_date - start_date <= 600
group by department_id
having count(employee_id) <= 1;

select department_id, min(hire_date) "minimum hire_date", max(hire_date) "maximum hire_date", round(avg(salary),2) "Salary"
from EMPLOYEES
where DEPARTMENT_ID is not null and HIRE_DATE is not null
group by department_id
order by (max(hire_date) - min(hire_date)) asc, avg(salary) desc;

select first_name || ' '|| last_name full_name, salary * 12 "Annual salary", COMMISSION_PCT, salary + ((12 * salary) * nvl(COMMISSION_PCT, -0.05)/100 ) "Next years salary" 
from employees;


select manager_id, count(employee_id), avg(salary)
from EMPLOYEES
where to_char(hire_date, 'MM') in('03', '09', '12') and manager_id is not null
group by manager_id
having avg(salary) = trunc(avg(salary),0);






