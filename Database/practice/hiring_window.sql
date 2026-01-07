select last_name, hire_date
from EMPLOYEES
where (hire_date between '01-JAN-1998' and '31-DEC-1998' )and (last_name not like 'K%')
order by hire_date asc