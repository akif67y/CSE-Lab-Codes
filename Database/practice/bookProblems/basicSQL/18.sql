select upper(substr(country_name,1,3) || '+'|| substr(country_name, length(country_name) - 2, 3)) "First name + Last Name"
from countries;

select lpad(concat(first_name, last_name), 60, '*')
from EMPLOYEES;

select job_title
from jobs
where instr(job_title, 'Manager') > 0;
