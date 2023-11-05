// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract BankAccount {
    address public owner;
    uint public balance;

    modifier onlyOwner() {
        require(msg.sender == owner, "Only the owner can call this function");
        _;
    }

    constructor() {
        owner = msg.sender;
        balance = 0;
    }

    function deposit(uint amount) public {
        require(amount > 0, "Amount should be greater than 0");
        balance += amount;
    }

    function withdraw(uint amount) public onlyOwner {
        require(amount > 0, "Amount should be greater than 0");
        require(balance >= amount, "Insufficient balance");
        balance -= amount;
    }

    function showBalance() public view returns (uint) {
        return balance;
    }

    function transfer(address to, uint amount) public onlyOwner {
        require(to != address(0), "Invalid address");
        require(to != owner, "Cannot transfer to the owner");
        require(balance >= amount, "Insufficient balance");
        
        balance -= amount;
        payable(to).transfer(amount);
    }
}
