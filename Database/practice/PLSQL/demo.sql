set serveroutput on;
BEGIN
    dbms_output.put_line('Hello World');
end;
/

DECLARE
    ename varchar2(100);
BEGIN
    select (first_name || last_name) into ename
    from EMPLOYEES
    where employee_id = 100;
    dbms_output.PUT_LINE('The name is : ' || ename);
end;
/
