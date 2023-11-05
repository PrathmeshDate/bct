// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentManagement {
    struct Student {
        uint256 id;
        string name;
        uint256 age;
        string major;
    }

    Student[] public students;
    address public owner;

    constructor() {
        owner = msg.sender;
    }

    modifier onlyOwner() {
        require(msg.sender == owner, "Only the owner can perform this operation");
        _;
    }

    function addStudent(uint256 _id, string memory _name, uint256 _age, string memory _major) public onlyOwner {
        students.push(Student(_id, _name, _age, _major));
    }

    function getStudentCount() public view returns (uint256) {
        return students.length;
    }

    function getStudent(uint256 index) public view returns (uint256, string memory, uint256, string memory) {
        require(index < students.length, "Invalid student index");
        Student memory student = students[index];
        return (student.id, student.name, student.age, student.major);
    }

    fallback() external payable {
        // Fallback function to receive Ether
    }
}
