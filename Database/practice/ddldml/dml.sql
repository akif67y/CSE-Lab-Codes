insert into person2 values ('59184477658689', 'Ahnaf Akif', '27-JUN-2005');
commit;

insert into person2 (nid, name) values (68405409858, 'Md Shahin Mollah' );
commit; 

insert into PERSON2
select nid, name, bdate
from PERSON
where nid <> '59184477658689';
commit;

CREATE TABLE my_employees AS SELECT * FROM HR.EMPLOYEES;
CREATE TABLE my_departments AS SELECT * FROM HR.DEPARTMENTS;
CREATE TABLE my_jobs AS SELECT * FROM HR.JOBS;

update MY_EMPLOYEES
set COMMISSION_PCT = 0
where COMMISSION_PCT is null;
commit;

update my_employees e1
set
e1.salary = (select max(e2.salary) from my_employees e2 group by e2.DEPARTMENT_ID having e2.department_id = e1.DEPARTMENT_ID);

update my_employees e1
set 
e1.COMMISSION_PCT =  e1.COMMISSION_PCT * (select count(*) from my_employees e2 where e2.manager_id = e1.EMPLOYEE_ID);

update my_employees e1
set 
e1.HIRE_DATE = trunc(e1.hire_date, 'YEAR')
where e1.hire_date < '01-JAN-2000';