select first_name ||' ' || last_name full_name, DEPARTMENTS.department_id ,department_name 
from employees, DEPARTMENTS
where employees.DEPARTMENT_ID = DEPARTMENTS.DEPARTMENT_ID and location_id = 1700