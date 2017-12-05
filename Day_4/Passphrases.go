// Author: MKozuch
// Date: 2017-12-05

package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func checkError(e error) {
	if e != nil {
		panic(e)
	}
}

func validatePassphrase(passphrase string) (bool, error) {
	items := strings.Split(passphrase, " ")
	sort.Strings(items)

	result := true

	for i := 0; i < len(items)-1; i++ {
		if items[i] == items[i+1] {
			result = false
			break
		}

	}

	return result, nil
}

type byLenLex []string

func (a byLenLex) Len() int {
	return len(a)
}
func (a byLenLex) Swap(i int, j int) {
	a[i], a[j] = a[j], a[i]
}
func (a byLenLex) Less(i int, j int) bool {
	if len(a[i]) < len(a[j]) {
		return true
	}
	if len(a[i]) > len(a[j]) {
		return false
	}
	return a[i] < a[j]
}

func validatePassphraseNewPolicy(passphrase string) (bool, error) {
	items := strings.Split(passphrase, " ")

	for i := 0; i < len(items); i++ {
		item := items[i]
		itemSplit := strings.Split(item, "")
		sort.Strings(itemSplit)
		item = strings.Join(itemSplit, "")
		items[i] = item
	}

	sort.Sort(byLenLex(items))

	result := true

	for i := 0; i < len(items)-1; i++ {
		if items[i] == items[i+1] {
			result = false
			break
		}
	}

	return result, nil
}

func main() {
	args := os.Args

	if len(args) <= 1 {
		fmt.Println("Test validate passphrase: ")

		passphrases := [...]string{
			"ala ma kota",
			"ala ma ala",
			"ala otak kota",
			"asdf aaaa ssss dddd ffff fsad",
			"spjb xkkak anuvk ejoklh nyerw bsjp zxuq vcwitnd xxtjmjg zfgq xkpf",
		}

		for _, element := range passphrases {
			isValid, _ := validatePassphrase(element)
			fmt.Printf("%s\n", element)
			fmt.Printf("\t%t\n", isValid)
		}

		fmt.Printf("\n")

		fmt.Println("Test validate passphrase new Policy: ")

		for _, element := range passphrases {
			isValid, _ := validatePassphraseNewPolicy(element)
			fmt.Printf("%s\n", element)
			fmt.Printf("\t%t\n", isValid)
		}

		os.Exit(0)
	}

	fileName := os.Args[1]
	fh, err := os.Open(fileName)
	checkError(err)
	defer fh.Close()

	scanner := bufio.NewScanner(fh)

	correctPassphrases := 0
	for scanner.Scan() {
		passphrase := scanner.Text()
		isValid, _ := validatePassphraseNewPolicy(passphrase)
		if isValid {
			correctPassphrases++
		}
	}
	fmt.Printf("%d\n", correctPassphrases)

	os.Exit(0)
}
